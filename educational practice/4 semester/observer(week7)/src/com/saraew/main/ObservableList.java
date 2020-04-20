package com.saraew.main;

import com.saraew.observer.Observable;
import com.saraew.observer.Observer;

import java.util.ArrayList;

public class ObservableList implements Observable {
    private String current;
    private ArrayList<Observer> observers;

    public ObservableList() {
        observers = new ArrayList<>();
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void deleteObserver(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers() {
        for (Observer observer : observers) {
            observer.update(current);
        }
    }

    public void setCurrent(String current) {
        this.current = current;
        notifyObservers();
    }
}
