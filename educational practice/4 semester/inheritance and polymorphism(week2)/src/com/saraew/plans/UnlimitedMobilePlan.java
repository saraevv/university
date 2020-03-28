package com.saraew.plans;

public class UnlimitedMobilePlan extends Plan {
    protected boolean isSharingAllowed;

    public UnlimitedMobilePlan(String name, int users, int price, boolean isSharingAllowed) {
        super(name, users, price);
        this.isSharingAllowed = isSharingAllowed;
    }

    public boolean isSharingAllowed() {
        return isSharingAllowed;
    }

    public void setSharingAllowed(boolean sharingAllowed) {
        isSharingAllowed = sharingAllowed;
    }

    @Override
    public String toString() {
        return "Unlimited mobile plan\n\tname: \"" + name + "\";\n\tusers: " + users + ";\n\tprice: " + price
                + ";\n\tis sharing allowed: " + isSharingAllowed() + ";\n";
    }

    @Override
    public boolean isCorrespond(Plan plan) {
        return super.isCorrespond(plan) && ((UnlimitedMobilePlan) plan).isSharingAllowed == this.isSharingAllowed;
    }
}
