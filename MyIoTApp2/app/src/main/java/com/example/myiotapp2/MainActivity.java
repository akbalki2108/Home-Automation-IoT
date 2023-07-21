package com.example.myiotapp2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.Response;
import com.android.volley.VolleyError;

import org.json.JSONException;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    String ipString = "192.168.29.162"; // replace with the IP address of your ESP32 device


    private static final String TAG = "MainActivity";
    private TextView textView;
    private Button button;
    private ESP32Connection esp32Connection;

    private Button mButton;
    private TextView mTextView;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.textView);
        button = findViewById(R.id.button);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                retrieveData();
                Toast.makeText(MainActivity.this, "command send", Toast.LENGTH_SHORT).show();
            }
        });

        // initiate a Switch
        Switch simpleSwitch = (Switch) findViewById(R.id.ledSwitch1);

        // check current state of a Switch (true or false).
//        Boolean switchState = simpleSwitch.isChecked();

        simpleSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    sendSignal("1");
                } else {
                    sendSignal("0");
                }
            }
        });



    }
    private  void sendSignal( String response){
        String command = "some_command";
//        String response = "some_response";
        String result = "";
        try {
            ESP32Connection connection = new ESP32Connection(ipString,getApplicationContext());
            if (connection.isConnected()) {
                try {
                    result = connection.sendCommand(command, response);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            } else {
                // handle connection failure
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void retrieveData() {

        esp32Connection = new ESP32Connection(ipString, getApplicationContext());
        esp32Connection.retrieveData(new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                // Handle the data here
                textView.setText(response);
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                // Handle the error here
                Log.e(TAG, "onError: " + error);
                Toast.makeText(MainActivity.this, "Failed to retrieve data: " + error, Toast.LENGTH_SHORT).show();
            }
        }, "status","led1");
    }
}