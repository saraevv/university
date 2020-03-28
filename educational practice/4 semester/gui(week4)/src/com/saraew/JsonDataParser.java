package com.saraew;


import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class JsonDataParser {
    public static ArrayList<Data> parse(String path) throws FileNotFoundException {
        GsonBuilder builder = new GsonBuilder();
        Gson gson = builder.create();
        JsonReader reader = new JsonReader(new FileReader(path));
        ArrayList<Data> out = gson.fromJson(reader, new TypeToken<List<Data>>() {
        }.getType());
        return out;
    }
}
