package com.MyOwnLife;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import java.util.Calendar;

/**
 * Created by ctt1414 on 3/29/2015.
 */
public class MyoBootReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        AlarmManager alarmMgr = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        PendingIntent pIntent = PendingIntent.getBroadcast(context, 0, new Intent(context, MyoAlarmReceiver.class), 0);
        long timeInMillis = Calendar.getInstance().getTimeInMillis();
        alarmMgr.setRepeating(AlarmManager.RTC_WAKEUP, timeInMillis, 0, pIntent);
    }
}
