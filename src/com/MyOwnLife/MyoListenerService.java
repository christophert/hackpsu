package com.MyOwnLife;

import android.app.*;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.os.ResultReceiver;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by ctt1414 on 3/29/2015.
 */
public class MyoListenerService extends IntentService {
    NotificationManager nm;

    public static final int STATUS_RUNNING = 0;
    public static final int STATUS_FINISHED = 1;
    public static final int STATUS_ERROR = 2;
    public static final String TAG = "ListenerService";


    public MyoListenerService() {
        super(MyoListenerService.class.getName());
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        Log.d(TAG, "Started");

        final ResultReceiver receiver = intent.getParcelableExtra("receiver");

        Bundle bundle = new Bundle();

        receiver.send(STATUS_RUNNING, Bundle.EMPTY);
        try {
            boolean result = readServerData();
            bundle.putBoolean("result", result);
            receiver.send(STATUS_FINISHED, bundle);
            if(result) {
                Intent launchIntent = getPackageManager().getLaunchIntentForPackage("com.MyOwnLife");
                startActivity(launchIntent);
            }
        }
        catch(Exception e) {
            bundle.putString(Intent.EXTRA_TEXT, e.toString());
            receiver.send(STATUS_ERROR, bundle);
        }
    }

    private boolean readServerData() throws IOException {
        try {
            URL url = new URL("http://myownlife-hpsu1.cloudapp.net/status.txt");

            BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()));
            String str = "No";
            while(in.readLine() != null) {
                str = in.readLine();
            }
            in.close();
            return str.equals("Yes");
        }
        catch(MalformedURLException e) {

        }
        catch(IOException e) {

        }
        return false;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
