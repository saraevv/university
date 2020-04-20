package com.saraew.main;


import com.saraew.observer.Observer;
import javafx.scene.control.Label;

public class ObserverLabel extends Label implements Observer {
    @Override
    public void update(String string) {
        this.setText(string);
    }
}
