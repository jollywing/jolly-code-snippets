
public class Wing
{
    private float length;
    private float height;

    public Wing(float length, float height) {
        this.length = length;
        this.height = height;
    }

    public void print() {
        System.out.printf("This Wing has %.2f length and %.2f height.\n",
                          length, height);
    }
    
}
