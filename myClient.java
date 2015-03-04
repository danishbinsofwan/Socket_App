
package transferapp;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class myClient {

  public final static int SOCKET_PORT = 6000;      // you may change this
  static int myPort = 0;
  String hostt;
  public final static String SERVER = "127.0.0.1";  // localhost
  public final static String
       FILE_TO_RECEIVED = "D:\\myNewFile.txt";  // you may change this, I give a
                                                            // different name because i don't want to
                                                            // overwrite the one used by server...

  public final static int FILE_SIZE = 602238600; // file size temporary hard coded
                                               // should bigger than the file to be downloaded

 void startMyClient(int port , String host)throws IOException {
    int bytesRead;
    int current = 0;
    FileOutputStream fos = null;
    BufferedOutputStream bos = null;
    Socket sock = null;
    
    
    myPort = port;
    hostt = host;
    
    try {
      sock = new Socket(hostt, myPort);
      System.out.println("Connecting...");

      // receive file
      byte [] mybytearray  = new byte [FILE_SIZE];
      InputStream is = sock.getInputStream();
      fos = new FileOutputStream(FILE_TO_RECEIVED);
      bos = new BufferedOutputStream(fos);
      bytesRead = is.read(mybytearray,0,mybytearray.length);
      current = bytesRead;

      do {
         bytesRead =
            is.read(mybytearray, current, (mybytearray.length-current));
         if(bytesRead >= 0) current += bytesRead;
      } while(bytesRead > -1);

      bos.write(mybytearray, 0 , current);
      bos.flush();
      System.out.println("File downloaded with directory address " + FILE_TO_RECEIVED + " of size " + current + " bytes");
    }
    finally {
      if (fos != null) fos.close();
      if (bos != null) bos.close();
      if (sock != null) sock.close();
    }
  }

}
