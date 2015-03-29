package com.MyOwnLife;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

/**
 * Created by ctt1414 on 3/29/2015.
 */
public class MyoAlarmReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        context.startService(new Intent(context, MyoListenerService.class));
    }
}
