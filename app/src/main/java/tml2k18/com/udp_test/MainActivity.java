package tml2k18.com.udp_test;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class MainActivity extends AppCompatActivity {
    Button b1,b2;
    TextView t1,t2,t3;
    String ipAdd,val1,totalval;
    int val=0;
    int tval;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b1=findViewById(R.id.btn1);
        b2=findViewById(R.id.btn2);
        t1=findViewById(R.id.txt1);
        t2=findViewById(R.id.txt2);
        t3=findViewById(R.id.txt3);
        b1.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        ipAdd=t1.getText().toString();

                        val1=t2.getText().toString().trim();
                        if((val1.equals(""))){
                         Toast t1=Toast.makeText(MainActivity.this,"Enter valid number plis",Toast.LENGTH_SHORT);
                         t1.show();

                        }
                        else {
                            val = Integer.parseInt(val1);
                            Tfunc(ipAdd,val);
                        }

                    }
                }
        );
        b2.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        totalval=getIntent().getStringExtra("val");
                        tval=Integer.parseInt(totalval);
                        Tfunc(ipAdd,tval);
                        t3.setText(totalval);
                    }
                }
        );


    }
    public void Tfunc(String a,int n){
        final String ip=a;
        final int val=n;
        Runnable ru=new Runnable() {
            @Override
            public void run() {
                int port=5000;

                try {
                    DatagramSocket udpSocket = new DatagramSocket(port);
                    InetAddress serverAddr = InetAddress.getByName(ip);
                    byte[] buf = String.valueOf(val).getBytes();
                    DatagramPacket packet = new DatagramPacket(buf, buf.length,serverAddr, port);
                    udpSocket.send(packet);

                    udpSocket.close();
                } catch (SocketException e) {
                    Log.e("Udp:", "Socket Error:", e);
                } catch (IOException e) {
                    Log.e("Udp Send:", "IO Error:", e);
                }
            }
        };
        Thread abc=new Thread(ru);
        abc.start();

    }


}



