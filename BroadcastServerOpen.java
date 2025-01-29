import java.net.*;
import java.io.*;

public class BroadcastServerOpen {
    public static void main(String[] args) {
        // create a open group of subnet
        String broadcastAddress = "255.255.255.255";
        int port = 5000;
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket();
            socket.setBroadcast(true);
            InetAddress group = InetAddress.getByName(broadcastAddress);

            while (true) {
            String message = "Hello from Broadcast Server in the group!";
            byte[] buffer = message.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, group, port);
            socket.send(packet);
            System.out.println("Sent: " + message);
            Thread.sleep(5000);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        } finally {
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        }
    }
}