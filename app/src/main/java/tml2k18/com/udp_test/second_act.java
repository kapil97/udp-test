package tml2k18.com.udp_test;

import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class second_act extends AppCompatActivity implements SensorEventListener{

    float sx,sy,sz;
    int tt;
    String tts;
    SensorManager sensorManager;
    Sensor accelerometer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        if(sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) !=null) {

            accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            sensorManager.registerListener(this,accelerometer,SensorManager.SENSOR_DELAY_NORMAL);

        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {

        sx= event.values[0];
        sy= event.values[1];
        sz= event.values[2];
        tt= (int) (sx+sy+sz/3);
        Intent it=new Intent(second_act.this,MainActivity.class);
        it.putExtra("val",String.valueOf(tt).trim());

    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}
