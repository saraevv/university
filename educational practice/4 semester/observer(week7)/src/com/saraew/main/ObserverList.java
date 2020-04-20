package com.saraew.main;

import com.saraew.observer.Observer;
import javafx.scene.control.ListView;

public class ObserverList extends ListView<String> implements Observer {
    @Override
    public void update(String string) {
        this.getItems().add(string);
    }
}
