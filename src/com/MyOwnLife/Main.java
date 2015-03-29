package com.MyOwnLife;

import android.app.Activity;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.view.*;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ImageView;

public class Main extends Activity {
    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }

    public void settingsV(View v){
        ImageView img = (ImageView)findViewById(R.id.imageView);
        img.setImageResource(R.drawable.unhealthy);
        TextView tv = (TextView)findViewById(R.id.textView3);
        tv.setText("Seizure");
        tv.setTextColor(Color.RED);
        TextView tv3 = (TextView)findViewById(R.id.textView7);

        new CountDownTimer(8000, 1000) {
            public void onTick(long msec) {

            }
            public void onFinish(){

            }
        }.start();
    }

    public void settingsH(View v){
        ImageView img2 = (ImageView)findViewById(R.id.imageView2);
        img2.setImageResource(R.drawable.unhealthy);
        TextView tv2 = (TextView)findViewById(R.id.textView6);
        tv2.setText("Seizure");
        tv2.setTextColor(Color.RED);
    }
}
