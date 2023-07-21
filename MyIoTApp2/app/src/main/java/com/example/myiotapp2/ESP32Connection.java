package com.example.myiotapp2;

import android.content.Context;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.util.HashMap;
import java.util.Map;

public class ESP32Connection {
    private String ip;
    private int port;
    private Context context;
    private static final String TAG = "ESP32Connection";
    private HttpURLConnection connection;
//    private RequestQueue requestQueue;

    public ESP32Connection(String ip, int port, Context context) {
        this.ip = ip;
        this.port = port;
        this.context = context;
//        this.requestQueue = Volley.newRequestQueue(context);
    }

    public ESP32Connection(String ip, Context context) {
        this.ip = ip;
        this.port = port;
        this.context = context;
//        this.requestQueue = Volley.newRequestQueue(context);
    }

    public void retrieveData(Response.Listener<String> successListener, Response.ErrorListener errorListener,String command,String key) {

        String url = "http://" + ip + "/"+command;

        RequestQueue queue = Volley.newRequestQueue(context);

        // Create a POST request with parameter
        Map<String, String> params = new HashMap<>();
        params.put("key", "value");

        JsonObjectRequest jsonObjectRequest = new JsonObjectRequest(Request.Method.GET, url, new JSONObject(params),
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            // Parse the JSON response
                            String data = response.getString(key);
                            successListener.onResponse(data);
                        } catch (JSONException e) {
                            errorListener.onErrorResponse(new VolleyError(e.getMessage()));
                        }
                    }
                }, errorListener);

        queue.add(jsonObjectRequest);
    }

    public boolean isConnected() {
        try {
            InetAddress address = InetAddress.getByName(ip);
            return address.isReachable(5000);
        } catch (IOException e) {
            Log.e(TAG, "IOException: " + e.getMessage());
            return false;
        }
    }

    public String sendCommand(String command, String response) throws IOException, JSONException {

        RequestQueue queue = Volley.newRequestQueue(context);
        String result = null;
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/json; charset=UTF-8");
        connection.setRequestProperty("Accept", "application/json");

        JSONObject postData = new JSONObject();
        postData.put("command", command);
        postData.put("response", response);

        OutputStream os = connection.getOutputStream();
        os.write(postData.toString().getBytes("UTF-8"));
        os.close();

        int responseCode = connection.getResponseCode();
        if (responseCode == HttpURLConnection.HTTP_OK) {
            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            StringBuilder responseBuilder = new StringBuilder();
            while ((inputLine = in.readLine()) != null) {
                responseBuilder.append(inputLine);
            }
            in.close();
            result = responseBuilder.toString();
        } else {
            throw new IOException("HTTP response code: " + responseCode);
        }
        return result;
    }


    public interface ESP32ResponseListener {
        void onResponseReceived(String response);
        void onResponseError(String errorMessage);
    }
}
