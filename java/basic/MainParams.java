
public class MainParams
{
    // args doesn't include the command, i.e. <java className>
    public static void main(String [] args) {
        if (args.length == 0) {
            System.out.println("execute this program with some params, Pls.");
            System.exit(1);
        }

        System.out.println("There are " + args.length + " params. ");
        for (String str: args) {
            System.out.println("+ " + str);
        }
    }
}
