package tml2k18.com.udp_test;

import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
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

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    Button b1;
    TextView t1,t2;
    String ipAdd;

    float sx,sy,sz;
    int tt;

    SensorManager sensorManager;
    Sensor accelerometer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b1=findViewById(R.id.btn1);
        t1=findViewById(R.id.txt1);

        t2=findViewById(R.id.txt2);
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        if(sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) !=null) {

            accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            sensorManager.registerListener(this,accelerometer,SensorManager.SENSOR_DELAY_NORMAL);

        }

        b1.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        ipAdd=t1.getText().toString();


                        if(ipAdd.equals("")){
                         Toast t1=Toast.makeText(MainActivity.this,"Enter valid number plis",Toast.LENGTH_SHORT);
                         t1.show();

                        }
                        else {

                            Tfunc(ipAdd,tt);
                        }

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


    @Override
    public void onSensorChanged(SensorEvent event) {
        sx= event.values[0];
        sy= event.values[1];
        sz= event.values[2];
        tt= (int) (sx+sy+sz/3);
        t2.setText(String.valueOf(tt));

    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}



