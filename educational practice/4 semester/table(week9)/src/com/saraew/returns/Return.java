package com.saraew.returns;

public abstract class Return {
    protected String type;

    public Return(String type) {
        this.type = type;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
