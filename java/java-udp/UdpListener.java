
/**
 * UdpListener: receive String on Udp port.
 * Author: WU Jiqing(jiqingwu@gmail.com)
 * Create: 2012-09-09
 * Update: 2012-09-09
 */

import java.net.DatagramSocket;
import java.net.SocketException;
import java.net.DatagramPacket;
import java.io.IOException;

class UdpListener
{
  public static void listen()
  {
    DatagramSocket udpSoc = null;

    try
    {
      udpSoc = new DatagramSocket(8888);
    }
    catch (SocketException e)
    {
      System.out.println("open socket failed, " +
                         "maybe the port is not available.");
    }

    byte [] buf = new byte[256];
    DatagramPacket packet = new DatagramPacket(buf, 256);

    while (true)
    {
      try
      {
        udpSoc.receive(packet);
        String msg = new String(packet.getData());
        System.out.println(msg);
        if(msg.startsWith("ByeBye"))
          break;
      }
      catch (IOException e)
      {
        System.out.println("receive data error!");
        break;
      }
    }
    
  }

  public static void main(String args[])
  {
    UdpListener.listen();
  }
}