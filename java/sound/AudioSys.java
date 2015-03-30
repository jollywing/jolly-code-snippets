
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Mixer.Info;
import javax.sound.sampled.Mixer;

public class AudioSys {
    public static void main(String args[]){
        Mixer.Info [] mixers;
        mixers = AudioSystem.getMixerInfo();
        for(Mixer.Info mixer: mixers){
            System.out.println(mixer.getDescription());
        }
    }
}
