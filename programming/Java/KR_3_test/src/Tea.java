public class Tea extends Drink {
    protected TeaType teaType;

    public Tea(String name, int caffeineCount, int price, TeaType teaType) {
        super(name, caffeineCount, price);
        this.teaType = teaType;
    }

    public Tea() {
    }

    @Override
    public String toString() {
        return super.toString() + "Tea type: " + teaType;
    }

    public TeaType getTeaType() {
        return teaType;
    }

    public void setTeaType(TeaType teaType) {
        this.teaType = teaType;
    }
}
