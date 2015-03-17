
public class PlayOgg
{
    public static void main(String args[])
    {
        OggClip ogg = new OggClip("alert.ogg");
        ogg.setGain(1.0F);
        ogg.play();
    }
}
