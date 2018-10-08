import java.util.List;
import java.util.ArrayList;


class FillListTask implements Runnable {
    private final int size;
    private List<String> strings;

    public FillListTask(int size) {
        this.size = size;
    }

    public synchronized boolean isFinished() {
        return null != strings;
    }

    public synchronized List<String> getList() {
        return strings;
    }

    @Override
    public void run() {
        List<String> strs = new ArrayList<String>(size);
        try {
            for (int i = 0; i < size; i++) {
                Thread.sleep(1000);
                strs.add("element " + String.valueOf(i));
            }
            synchronized(this){
                strings = strs;
                this.notifyAll();
            }
        }
        catch (InterruptedException e) {
        }
    }

    public static void main(String[] args) throws InterruptedException {
        FillListTask task = new FillListTask(6);
        new Thread(task).start();
        synchronized(task) {
            while (!task.isFinished()) {
                task.wait();
            }
        }
        System.out.println("Array full: " + task.getList());

    }
}
