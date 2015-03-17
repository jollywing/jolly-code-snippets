
/**
 * UdpBroker: provide static method to send packet with UDP.
 * Author: WU Jiqing(jiqingwu@gmail.com)
 * Create: 2012-09-09
 * Update: 2012-09-09
 */

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.io.IOException;
import java.net.SocketException;
import java.net.InetAddress;
import java.net.UnknownHostException;

class UdpBroker
{
  private DatagramSocket udpSoc;

  public UdpBroker()
  {
  }

  public boolean open(String ip, int port)
  {
    try
    {
      udpSoc = new DatagramSocket();
    }
    catch (SocketException e)
    {
      System.out.println("open socket failed, " +
                         "maybe the port is not available.");
      return false;
    }

    try
    {
      InetAddress addr = InetAddress.getByName(ip);
      udpSoc.connect(addr, port);
    }
    catch (UnknownHostException e)
    {
      System.out.println("unknown host, maybe the given IP is wrong.");
      return false;
    }

    return true;
  }

  public void close()
  {
    udpSoc.disconnect();
  }

  public boolean send(String msg)
  {
    byte [] msgBytes = msg.getBytes();
    DatagramPacket packet =
        new DatagramPacket(msgBytes, msgBytes.length);
    try
    {
      udpSoc.send(packet);
    }
    catch(IOException e)
    {
      System.out.println("send packet failed!");
      return false;
    }
    return true;
  }

  public static void main(String args[])
  {
    UdpBroker broker = new UdpBroker();
    if (broker.open("127.0.0.1", 8888))
    {
      broker.send("Hello");
      broker.send("ByeBye");
      broker.close();
    }
  }
}