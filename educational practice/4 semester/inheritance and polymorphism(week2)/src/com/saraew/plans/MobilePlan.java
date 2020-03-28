package com.saraew.plans;

public abstract class MobilePlan extends Plan {
    protected double pricePerMinute;
    protected double pricePerSMS;
    protected double pricePerMegabyte;

    public MobilePlan(String name, int users, double price, double pricePerMinute, double pricePerSMS, double pricePerMegabyte) {
        super(name, users, price);
        this.pricePerMinute = pricePerMinute;
        this.pricePerSMS = pricePerSMS;
        this.pricePerMegabyte = pricePerMegabyte;
    }

    public double getPricePerMinute() {
        return pricePerMinute;
    }

    public void setPricePerMinute(double pricePerMinute) {
        this.pricePerMinute = pricePerMinute;
    }

    public double getPricePerSMS() {
        return pricePerSMS;
    }

    public void setPricePerSMS(double pricePerSMS) {
        this.pricePerSMS = pricePerSMS;
    }

    public double getPricePerMegabyte() {
        return pricePerMegabyte;
    }

    public void setPricePerMegabyte(double pricePerMegabyte) {
        this.pricePerMegabyte = pricePerMegabyte;
    }

    @Override
    public String toString() {
        return "Mobile plan\n\ttype: \"" + this.getClass().getName() + "\";\n\tname: \"" + name + "\";\n\tusers: " + users +
                ";\n\tprice: " + price + ";\n\tprice per minute: " + pricePerMinute + ";\n\tprice per SMS: " + pricePerSMS +
                ";\n\tprice per megabyte: " + pricePerMegabyte + ";\n";
    }

    @Override
    public boolean isCorrespond(Plan plan) {
        return super.isCorrespond(plan) && ((MobilePlan) plan).pricePerMegabyte >= this.pricePerMegabyte &&
                ((MobilePlan) plan).pricePerMinute >= this.pricePerMinute && ((MobilePlan) plan).pricePerSMS >= this.pricePerSMS;
    }
}
