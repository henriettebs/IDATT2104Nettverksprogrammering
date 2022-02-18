package obligP4;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try {
            InetAddress address = InetAddress.getLocalHost(); // getByName()
            DatagramSocket datagramSocket = new DatagramSocket();

            Scanner scanner = new Scanner(System.in);
            //String echoString;
            String number1;
            String operator;
            String number2;

            do{
                //System.out.println("Enter string to be echoed; ");
                //echoString = scanner.nextLine(); //Getting input from user

                //byte[] buffer = echoString.getBytes(); //converting user-input to a byte-array
                System.out.println("Enter the first number: ");
                number1 = scanner.nextLine();
                byte[] byteNumber1 = number1.getBytes();
                DatagramPacket packet = new DatagramPacket(byteNumber1, byteNumber1.length, address, 5000); //Creates packet
                datagramSocket.send(packet);

                System.out.println("Enter the preferred operator: ");
                operator = scanner.nextLine();
                byte[] byteOperator = operator.getBytes();
                packet = new DatagramPacket(byteOperator, byteOperator.length, address, 5000); //Updates packet
                datagramSocket.send(packet);

                System.out.println("Enter the second number: ");
                number2 = scanner.nextLine();
                byte[] byteNumber2 = number2.getBytes();
                packet = new DatagramPacket(byteNumber2, byteNumber2.length, address, 5000); //Updates packet
                datagramSocket.send(packet);

                byte[] messageFromServer = new byte[50];
                packet = new DatagramPacket(messageFromServer, messageFromServer.length);
                datagramSocket.receive(packet);
                System.out.println(new String(messageFromServer, 0, packet.getLength()));

            }while(!number1.equals("exit"));

        } catch(SocketTimeoutException e) {
            System.out.println("The socket timed out");
        } catch(IOException e){
            System.out.println("Client error: " + e.getMessage());
        }
    }
}
