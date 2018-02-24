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
    long currt;
    String ipAdd;

    float xt,yt,zt,axt,ayt,azt;
    int rt;
    int i,temp[] = new int[36];

    SensorManager sensorManager;
    Sensor accelerometer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        for (i=0;i<36;i++)
            temp[i] = 0;

        b1=findViewById(R.id.btn1);
        t1=findViewById(R.id.txt1);

        t2=findViewById(R.id.txt2);
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                currt=System.currentTimeMillis();
                if(sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) !=null) {
                    accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
                    sensorManager.registerListener(MainActivity.this,accelerometer,SensorManager.SENSOR_DELAY_NORMAL);
                    b1.setEnabled(false);
                }
            }
        });
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
    public void onSensorChanged(final SensorEvent event) {
        ipAdd=t1.getText().toString();
        if(ipAdd.equals("")){
            Toast toast=Toast.makeText(MainActivity.this,"Enter valid number plis",Toast.LENGTH_SHORT);
            toast.show();

        }
        else {

            for(i=0;i<36;i++) {
                if ((System.currentTimeMillis() - currt) / 1000 <= (i + 1) * 5 && (System.currentTimeMillis() - currt) / 1000 >= i * 5 && i == 0) {

                    xt = event.values[0];
                    axt+=Math.abs(xt);
                    yt =  event.values[1];
                    ayt+=Math.abs(yt);
                    zt =  event.values[2];
                    azt+=Math.abs(zt);
                    rt= (int) (axt+ayt+azt);
                    t2.setText(String.valueOf(rt).trim());

                } else if ((System.currentTimeMillis() - currt) / 1000 <= (i + 1) * 5 && (System.currentTimeMillis() - currt) / 1000 >= i * 5) {

                    if (temp[i - 1] == 0) {
                        xt = 0;
                        yt = 0;
                        zt = 0;
                        axt=0;
                        ayt=0;
                        azt=0;
                        temp[i - 1] = 1;
                        Log.d("Itna Second ka data:", " " + (i - 1));

                        Tfunc(ipAdd, rt);

                    }

                    xt = event.values[0];
                    axt+=Math.abs(xt);
                    yt =  event.values[1];
                    ayt+=Math.abs(yt);
                    zt =  event.values[2];
                    azt+=Math.abs(zt);
                    rt= (int) (axt+ayt+azt);
                    t2.setText(String.valueOf(rt).trim());

                } else if ((System.currentTimeMillis() - currt) / 1000 >= 180 && temp[35] == 0) {

                    Tfunc(ipAdd, rt);
                    Log.d("Itna Second ka data:", "35");
                    temp[35] = 1;

                }
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}



