public class Coffee extends Drink {
    protected CoffeeType coffeeType;

    public Coffee(String name, int caffeineCount, int price, CoffeeType coffeeType) {
        super(name, caffeineCount, price);
        this.coffeeType = coffeeType;
    }

    public Coffee() {
    }

    @Override
    public String toString() {
        return super.toString() + "Coffee type: " + coffeeType;
    }

    public CoffeeType getCoffeeType() {
        return coffeeType;
    }

    public void setCoffeeType(CoffeeType coffeeType) {
        this.coffeeType = coffeeType;
    }
}
