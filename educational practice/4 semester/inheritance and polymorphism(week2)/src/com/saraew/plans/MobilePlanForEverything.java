package com.saraew.plans;

public class MobilePlanForEverything extends MobilePlanForCallsAndSMS {
    protected int countOfMegabytes;
    protected boolean isInternetUnlimited;

    public MobilePlanForEverything(String name, int users, double price, double pricePerMinute, double pricePerSMS, double pricePerMegabyte,
                                   int freeMinutes, int countOfFavoriteNumbers, boolean isCallsUnlimited, int countOfSMS,
                                   boolean isSMSUnlimited, int countOfMegabytes, boolean isInternetUnlimited) {
        super(name, users, price, pricePerMinute, pricePerSMS, pricePerMegabyte, freeMinutes, countOfFavoriteNumbers, isCallsUnlimited, countOfSMS, isSMSUnlimited);
        this.countOfMegabytes = countOfMegabytes;
        this.isInternetUnlimited = isInternetUnlimited;
    }

    public int getCountOfMegabytes() {
        return countOfMegabytes;
    }

    public void setCountOfMegabytes(int countOfMegabytes) {
        this.countOfMegabytes = countOfMegabytes;
    }

    public boolean isInternetUnlimited() {
        return isInternetUnlimited;
    }

    public void setInternetUnlimited(boolean internetUnlimited) {
        isInternetUnlimited = internetUnlimited;
    }

    @Override
    public String toString() {
        return super.toString() + "\tcount of megabytes: " + countOfMegabytes + ";\n\tis internet unlimited: " + isInternetUnlimited + ";\n";
    }

    @Override
    public boolean isCorrespond(Plan plan) {
        return super.isCorrespond(plan) && ((MobilePlanForEverything) plan).isInternetUnlimited == this.isInternetUnlimited &&
                ((MobilePlanForEverything) plan).countOfMegabytes <= this.countOfMegabytes;
    }
}
