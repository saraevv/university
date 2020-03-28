package com.saraew.plans;

public class ComputerPlan extends Plan {
    protected int internetSpeed;

    public ComputerPlan(String name, int users, double price, int internetSpeed) {
        super(name, users, price);
        this.internetSpeed = internetSpeed;
    }

    public int getInternetSpeed() {
        return internetSpeed;
    }

    public void setInternetSpeed(int internetSpeed) {
        this.internetSpeed = internetSpeed;
    }

    @Override
    public String toString() {
        return "Computer plan\n\tname: \"" + name + "\";\n\tusers: " + users + ";\n\tprice: " + price
                + ";\n\tinternet speed: " + internetSpeed + ";\n";

    }

    @Override
    public boolean isCorrespond(Plan plan) {
        return super.isCorrespond(plan) && this.getInternetSpeed() >= ((ComputerPlan) plan).getInternetSpeed();
    }
}
