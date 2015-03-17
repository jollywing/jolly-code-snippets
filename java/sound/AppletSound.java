
import java.applet.Applet;
import java.applet.AudioClip;
import java.net.URL;

public class AppletSound {
    public static void main(String args[]){
        try{
            // new audio clip;
            URL url = new URL("file:alert.wav");
            AudioClip clip = Applet.newAudioClip(url);
            // clip play
            clip.play();
        } catch (java.net.MalformedURLException e) {
            e.printStackTrace();
        }
    }
}
