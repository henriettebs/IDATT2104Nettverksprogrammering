package obligP4;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class Main {

    public static void main(String[] args) {
        try{
            DatagramSocket socket = new DatagramSocket(5000);

            while(true){
                byte[] byteNumber1 = new byte[10];
                DatagramPacket packet = new DatagramPacket(byteNumber1, byteNumber1.length);
                socket.receive(packet);
                String num1FromClient = new String(byteNumber1, 0, packet.getLength());
                int num1 = Integer.parseInt(num1FromClient);

                byte[] byteOperator = new byte[10];
                packet = new DatagramPacket(byteOperator, byteOperator.length);
                socket.receive(packet);
                String operator = new String(byteOperator, 0, packet.getLength());

                byte[] byteNumber2 = new byte[10];
                packet = new DatagramPacket(byteNumber2, byteNumber2.length);
                socket.receive(packet);
                String num2FromClient = new String(byteNumber2, 0, packet.getLength());
                int num2 = Integer.parseInt(num2FromClient);

                String calculation = num1FromClient+" "+operator+" "+num2FromClient+" = "+calculate(num1, operator, num2);
                System.out.println("Calculation received is: "+calculation);

                String answerToClient = "Echo of calculation from UDP Server: " + calculation;
                byte[] byteAnswer = answerToClient.getBytes();
                InetAddress address = packet.getAddress();
                int port = packet.getPort();
                packet = new DatagramPacket(byteAnswer, byteAnswer.length, address, port);
                socket.send(packet);
            }
            /*while(true) {
                byte[] buffer = new byte[50];
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                String messageFromClient = new String(buffer, 0, packet.getLength());
                //if(messageFromClient.equals("Close down server")) break; //Closes down server, which the client shouldn't be allowed to do
                if(messageFromClient.equals("exit")) System.out.println("Client shut down");
                System.out.println("Text received is: " + messageFromClient);


                String returnString = "echo from server: " + messageFromClient;
                byte[] buffer2 = returnString.getBytes();
                InetAddress address = packet.getAddress();
                int port = packet.getPort();
                packet = new DatagramPacket(buffer2, buffer2.length, address, port);
                socket.send(packet);
            }*/
        } catch(SocketException e) {
            System.out.println("SocketException: " + e.getMessage());
        } catch(IOException e) {
            System.out.println("IOException: " + e.getMessage());
        }
    }
    public static int calculate(int num1, String operator, int num2){
        if(operator.equals("+")) return num1 + num2;
        if(operator.equals("-")) return num1 - num2;
        if(operator.equals("*")) return num1 * num2;
        if(operator.equals("/")) return num1 / num2;
        return 0;
    }
}
