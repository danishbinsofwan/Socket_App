/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package transferapp;

import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author sahmed.seecs
 */
public class myUnit {
    
    public static void main(String args[]) throws IOException
    {
        
      myServer server = new myServer();
      myClient client = new myClient();
      
      // Unit Test 1 right args i.e port and host, 
      System.out.println("You're in the client mode\n");
      client.startMyClient(6000, "127.0.0.1");
      
      // Unit Test 2 wrong port
      //System.out.println("You're in the client mode\n");
      //client.startMyClient(534534, "127.0.0.1");
      
      // Unit test 3 wrong host
      //System.out.println("You're in the client mode\n");
      //client.startMyClient(6000, "898989");
    }
   
}
