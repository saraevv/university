package com.saraew.plans;

abstract public class Plan {
    protected String name;
    protected int users;
    protected double price;

    public Plan(String name, int users, double price) {
        this.name = name;
        this.users = users;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getUsers() {
        return users;
    }

    public void setUsers(int users) {
        this.users = users;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public abstract String toString();

    public boolean isCorrespond(Plan plan) {
        return this.getClass().equals(plan.getClass()) && this.price <= plan.price;
    }
}
