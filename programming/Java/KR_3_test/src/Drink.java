public abstract class Drink {
    protected String name;
    protected int caffeineCount;
    protected int price;

    public Drink(String name, int caffeineCount, int price) {
        this.name = name;
        this.caffeineCount = caffeineCount;
        this.price = price;
    }

    public Drink() {
    }

    @Override
    public String toString() {
        return "Drink type: " + this.getClass().getName() + "; Name: " + name + "; Caffeine count: " + caffeineCount + "; Price: " + price + "; ";
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCaffeineCount() {
        return caffeineCount;
    }

    public void setCaffeineCount(int caffeineCount) {
        this.caffeineCount = caffeineCount;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
