// Java implementation of Server side
// It contains two classes : Server and ClientHandler
// Save file as Server.java

import java.io.*;
import java.util.*;
import java.net.*;

// Server class
public class Server
{

	// Vector to store active clients
	static Vector<ClientHandler> ar = new Vector<>();
	static Vector<Thread> thr= new Vector<>();
	// counter for clients
	static int i = 0;

	public static void main(String[] args) throws IOException
	{
		Scanner sc = new Scanner(System.in);

		// server is listening on port 1234
		ServerSocket ss = new ServerSocket(1234);

		Socket s;
		
		Thread sendMessage = new Thread(new Runnable()
		{   Scanner scn = new Scanner(System.in);

			@Override
			public void run() {
				while (true) {

					// read the message to deliver.
					String msg = scn.nextLine();
					
					try {   
					if(msg.equals("BCT"))
					for (ClientHandler mc : Server.ar)
							mc.dos.writeUTF(msg);
						// write on the output stream
						//dos.writeUTF(msg);
					} catch (IOException e) {
						System.exit(0);
						e.printStackTrace();
					}
				}
			}
		});
		sendMessage.start();

		// running infinite loop for getting
		// client request
		while (true)
		{
			// Accept the incoming request
			s = ss.accept();

			System.out.println("New client request received : " + s);

			// obtain input and output streams
			DataInputStream dis = new DataInputStream(s.getInputStream());
			DataOutputStream dos = new DataOutputStream(s.getOutputStream());

			System.out.println("Creating a new handler for this client...");

			// Create a new handler object for handling this request.
			ClientHandler mtch = new ClientHandler(s,"client " + i, dis, dos);

			// Create a new Thread with this object.
			Thread t = new Thread(mtch);

			System.out.println("Adding this client to active client list");

			// add this client to active clients list
			ar.add(mtch);
			thr.add(t);
			// start the thread.
			t.start();

			// increment i for new client.
			// i is used for naming only, and can be replaced
			// by any naming scheme
			i++;
		}
	}
}

// ClientHandler class
class ClientHandler implements Runnable
{
	Scanner scn = new Scanner(System.in);
	private String name;
	final DataInputStream dis;
	final DataOutputStream dos;
	Socket s;
	boolean isloggedin;
	boolean welcome;

	// constructor
	public ClientHandler(Socket s, String name, DataInputStream dis, DataOutputStream dos) 
	{
		this.dis = dis;
		this.dos = dos;
		this.name = name;
		this.s = s;
		this.isloggedin=true;
		this.welcome=true;
	}

	@Override
	public void run() {

		String received;
		while (true)
		{
			try
			{

				//for client joining a room,
				if(this.welcome)
				{
					//client will get list of all other active clients
						for (ClientHandler mc : Server.ar)
						if(mc.name != this.name)
							this.dos.writeUTF(mc.name+":"+"is active");
							
					//sending logging info of client to other users.....................
						for (ClientHandler mc : Server.ar)
						if(mc.name != this.name)
							mc.dos.writeUTF("--------"+this.name+":"+"is online");	
				}
				this.welcome=false;

				// receive the string
				received = dis.readUTF();

				System.out.println(received);

				if(received.equals("logout"))
				{
					//sending logout message to all clients....................
					for (ClientHandler mc : Server.ar)
						if(mc.name != this.name)
							mc.dos.writeUTF(this.name+":"+"is logged out");
					
					
					this.isloggedin=false;
					this.s.close();
					Server.ar.remove(this);
					break;
				}
				
				if(received.equals("Active"))
				{
					for (ClientHandler mc : Server.ar)
						if ((!mc.name.equals(this.name)))
							{
								this.dos.writeUTF(mc.name+":"+"is active");
							}
				}
				
				if(received.equals("Quit"))
				{
				for (Thread th : Server.thr)
				{
				//this.dos.writeUTF(mc.name+":"+"is active");
				th.interrupt();
				}
				
				}
				// break the string into message and recipient part
				StringTokenizer st = new StringTokenizer(received, "#");
				
				String MsgToSend = st.nextToken();
				//System.out.println(MsgToSend);
				String recipient = st.nextToken();
				String[] arr = recipient.split(",", 0);  
				//sending to multiple client
				//StringTokenizer st_rec = new StringTokenizer(recipient,",");
				// while (st_rec.hasMoreTokens()) 
           			//	 System.out.println(st_rec.nextToken()); 
				//String recipient = st.nextToken();
				//System.out.println(recipient);

				// search for the recipient in the connected devices list.
				// ar is the vector storing client of active users
				
				 for (String w : arr) 
				for (ClientHandler mc : Server.ar)
				{     
				
					//recipient = st_rec.nextToken();
						///System.out.println(recipient);	
					// if the recipient is found, write on its
					// output stream
					if ((mc.name.equals(w))&&(!mc.name.equals(this.name)))
					{
						mc.dos.writeUTF(this.name+" : "+MsgToSend);
						
					}
				}
			} 
			catch (IOException e) 
			
			{
				System.exit(0);
				e.printStackTrace();
			}

		}
		try
		{
			// closing resources
			this.dis.close();
			this.dos.close();

		}
		catch(IOException e)
		{
			System.exit(0);
			e.printStackTrace();
		}
	}
}
