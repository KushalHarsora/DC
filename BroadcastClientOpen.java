import java.net.*;
import java.io.*;

public class BroadcastClientOpen {
    public static void main(String[] args) {
        int port = 5000;
        DatagramSocket socket = null;
        
        try {
            socket = new DatagramSocket(port);
            socket.setBroadcast(true);

            while (true) {
                byte[] buffer = new byte[256];
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                String message = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received: " + message);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        }
    }
}