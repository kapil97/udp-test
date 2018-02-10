package tml2k18.com.udp_test;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class MainActivity extends AppCompatActivity{
    Button b1;
    int port=5000;
    String ip="192.168.137.227";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
         b1=findViewById(R.id.btn1);
        b1.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        try {
                            int i=8;
                            DatagramSocket udpSocket = new DatagramSocket(port);
                            InetAddress serverAddr = InetAddress.getByName(ip);
                            byte[] buf = String.valueOf(i).getBytes();
                            DatagramPacket packet = new DatagramPacket(buf, buf.length,serverAddr, port);
                            udpSocket.send(packet);
                        } catch (SocketException e) {
                            Log.e("Udp:", "Socket Error:", e);
                        } catch (IOException e) {
                            Log.e("Udp Send:", "IO Error:", e);
                        }

                    }
                }
        );

    }





}



