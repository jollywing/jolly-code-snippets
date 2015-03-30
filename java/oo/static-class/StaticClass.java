
class Laptop {

    // non-static inner class
    class KeyBord {
        // vendorID shadowed the vendorID of Laptop
        // If you want to access the vendorID of Laptop,
        // you can write like this: Laptop.this.vendorID
        private String vendorID;

        private int keyCount;
        // non-static class cannot has static member variable,
        // but it can have static constant.
        private static final String LAYOUT = "US";
        // private static boolean withFuncKey = true;

        // non-static class can not declare a static method
        // neither the static final method
        // public static String getLayout(){
        //     return LAYOUT;
        // }
        public String getLayout(){
            return LAYOUT;
        }

        // Java support default constructor which set keyCount to 0
        // If you write a constructor,
        // then java won't create the default constructor
        // So if your constructor has params, 
        // you can not construct it without params any more.
        public KeyBord(int keyCount){
            this.keyCount = keyCount;
        }

        public int keyCount(){
            return keyCount;
        }

        // although vendorId and model is private member of outer class,
        // the non-static inner class can access it.
        public void print(){
            System.out.printf("%s %s has a keybord with %d keys.\n",
                              Laptop.this.vendorID, model, keyCount);
        }
    }

    static class Battery {
        // static inner class can have static data member
        public static String vendorID = "intel";
        private boolean chared;

        // static inner class can have static method
        public static void print(){
            System.out.println("The battery is made in " + vendorID);
            // static inner class can access the static member of outer class
            System.out.println("It can support " + VOLTAGE + " voltage.");
        }

        public boolean charged(){
            return chared;
        }

        // static inner class can not access non-static member of outer class
        // public String laptopInfo(){
        //     return model;
        // }
    }

    private String vendorID;
    private String model;
    private int price;          // $ (dollar)
    private KeyBord keybord;
    public static int VOLTAGE = 40; // unit V

    // The default constructor won't construct inner class instance,
    // you need construct it explicitly.
    public Laptop() {
        vendorID = "Lenovo";
        model = "T42";
        price = 12000;
        keybord = new KeyBord(104);
    }

    public KeyBord getKeyBord()
    {
        return keybord;
    }

}

// You can not declare a standalone class as static!
// static class Computer {
//     private static String vendorID;
//     private static String model;
// }

public class StaticClass {
    public static void main(String args[]){
        Laptop laptop = new Laptop();
        // System.out.println(Laptop.KeyBord.getLayout());

        // the instance of non-static inner class can not be created separately
        // Laptop.KeyBord keyboard = new Laptop.KeyBord(104);
        Laptop.KeyBord keyboard = laptop.getKeyBord();
        // Or you can create a KeyBord instance like this:
        // Laptop.KeyBord keyboard = laptop.new KeyBord(104);
        if(keyboard != null)
            keyboard.print();

        Laptop.Battery.print();
        // the static inner class can be instanced separately.
        Laptop.Battery battery = new Laptop.Battery();
    }
}
