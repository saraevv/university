package com.saraew.plans;

public class MobilePlanForCalls extends MobilePlan {
    protected int freeMinutes;
    protected int countOfFavoriteNumbers;
    protected boolean isCallsUnlimited;

    public MobilePlanForCalls(String name, int users, double price, double pricePerMinute,
                              double pricePerSMS, double pricePerMegabyte, int freeMinutes, int countOfFavoriteNumbers, boolean isCallsUnlimited) {
        super(name, users, price, pricePerMinute, pricePerSMS, pricePerMegabyte);
        this.freeMinutes = freeMinutes;
        this.countOfFavoriteNumbers = countOfFavoriteNumbers;
        this.isCallsUnlimited = isCallsUnlimited;
    }

    public int getFreeMinutes() {
        return freeMinutes;
    }

    public void setFreeMinutes(int freeMinutes) {
        this.freeMinutes = freeMinutes;
    }

    public int getCountOfFavoriteNumbers() {
        return countOfFavoriteNumbers;
    }

    public void setCountOfFavoriteNumbers(int countOfFavoriteNumbers) {
        this.countOfFavoriteNumbers = countOfFavoriteNumbers;
    }

    public boolean isCallsUnlimited() {
        return isCallsUnlimited;
    }

    public void setCallsUnlimited(boolean callsUnlimited) {
        isCallsUnlimited = callsUnlimited;
    }

    @Override
    public String toString() {
        return super.toString() + "\tfree minutes: " + freeMinutes + ";\n\tcount of favorite numbers: " + countOfFavoriteNumbers +
                ";\n\tis calls unlimited: " + isCallsUnlimited + ";\n";
    }

    @Override
    public boolean isCorrespond(Plan plan) {
        return super.isCorrespond(plan) && ((MobilePlanForCalls) plan).isCallsUnlimited == this.isCallsUnlimited &&
                ((MobilePlanForCalls) plan).countOfFavoriteNumbers <= this.countOfFavoriteNumbers &&
                ((MobilePlanForCalls) plan).freeMinutes <= this.freeMinutes;
    }
}
