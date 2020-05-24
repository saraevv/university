package com.saraew.stuff;

public class Pair<T extends Comparable<T>, V extends Comparable<V>> implements Comparable<Pair<T, V>> {
    private T first;
    private V second;

    public Pair(T first, V second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public void setFirst(T first) {
        this.first = first;
    }

    public V getSecond() {
        return second;
    }

    public void setSecond(V second) {
        this.second = second;
    }

    @Override
    public boolean equals(Object obj) {
        Pair<T, V> p = (Pair<T, V>) obj;
        return this.first.equals(p.first) && this.second.equals(p.second);
    }

    @Override
    public int compareTo(Pair<T, V> tvPair) {
        if (this.getFirst().equals(tvPair.getFirst())) {
            return this.getSecond().compareTo(tvPair.getSecond());
        } else {
            return this.getFirst().compareTo(tvPair.getFirst());
        }
    }
}
