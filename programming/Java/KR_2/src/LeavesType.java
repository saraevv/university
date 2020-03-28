public enum LeavesType {
    FOLIAR,
    CONIFEROUS,
    INDEFINITE;

    public static LeavesType valueFromString(String s) {
        if (s.equals("foliar")) {
            return FOLIAR;
        } else if (s.equals("coniferous")) {
            return CONIFEROUS;
        } else {
            return INDEFINITE;
        }
    }
}
