/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-18
 **/

import java.util.Random;

class Sleep
{
    private static Random R = new Random();
    public void update() {
        System.out.println("generating a random integer ...");
        // wait 1 second.
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        int random = R.nextInt();
        System.out.println("" + random);
    }

    public static void main(String args[]) {
        Sleep s = new Sleep();
        while(true) {
            s.update();
        }
    }
}
