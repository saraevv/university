package com.saraew.plans;

public class MobilePlanForCallsAndSMS extends MobilePlanForCalls {
    protected int countOfSMS;
    protected boolean isSMSUnlimited;

    public MobilePlanForCallsAndSMS(String name, int users, double price, double pricePerMinute, double pricePerSMS,
                                    double pricePerMegabyte, int freeMinutes, int countOfFavoriteNumbers, boolean isCallsUnlimited,
                                    int countOfSMS, boolean isSMSUnlimited) {
        super(name, users, price, pricePerMinute, pricePerSMS, pricePerMegabyte, freeMinutes, countOfFavoriteNumbers, isCallsUnlimited);
        this.countOfSMS = countOfSMS;
        this.isSMSUnlimited = isSMSUnlimited;
    }

    public int getCountOfSMS() {
        return countOfSMS;
    }

    public void setCountOfSMS(int countOfSMS) {
        this.countOfSMS = countOfSMS;
    }

    public boolean isSMSUnlimited() {
        return isSMSUnlimited;
    }

    public void setSMSUnlimited(boolean SMSUnlimited) {
        isSMSUnlimited = SMSUnlimited;
    }

    @Override
    public String toString() {
        return super.toString() + "\tcount of SMS: " + countOfSMS + ";\n\tis SMS unlimited: " + isSMSUnlimited + ";\n";
    }

    @Override
    public boolean isCorrespond(Plan plan) {
        return super.isCorrespond(plan) && ((MobilePlanForCallsAndSMS) plan).isSMSUnlimited == this.isSMSUnlimited &&
                ((MobilePlanForCallsAndSMS) plan).countOfSMS <= this.countOfSMS;
    }
}
