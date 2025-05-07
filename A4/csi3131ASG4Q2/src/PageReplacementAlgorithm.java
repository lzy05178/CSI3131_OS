import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

public class PageReplacementAlgorithm {
    private List<Integer> pageReferenceString;
    private int numFrames;

    public PageReplacementAlgorithm(List<Integer> pageReferenceString, int numFrames) {
        this.pageReferenceString = pageReferenceString;
        this.numFrames = numFrames;
    }

    public static List<Integer> generatePageReferenceString(int length) {
        List<Integer> pageReferenceString = new ArrayList<>();
        Random random = new Random();
        for (int i = 0; i < length; i++) {
            pageReferenceString.add(random.nextInt(10));
        }
        return pageReferenceString;
    }

    public int fifo() {
        int pageFaults = 0;
        List<Integer> pageFrames = new ArrayList<>();
        for (int page : pageReferenceString) {
            if (!pageFrames.contains(page)) {
                pageFaults++;
                if (pageFrames.size() < numFrames) {
                    pageFrames.add(page);
                } else {
                    pageFrames.remove(0);
                    pageFrames.add(page);
                }
            }
        }
        return pageFaults;
    }

    public int lru() {
        int pageFaults = 0;
        List<Integer> pageFrames = new ArrayList<>();
        Map<Integer, Integer> pageLastUsed = new HashMap<>();
        for (int page : pageReferenceString) {
            if (!pageFrames.contains(page)) {
                pageFaults++;
                if (pageFrames.size() < numFrames) {
                    pageFrames.add(page);
                } else {
                    int leastRecentlyUsedPage = pageLastUsed.entrySet().stream()
                            .min(Map.Entry.comparingByValue())
                            .get().getKey();
                    pageFrames.remove((Integer) leastRecentlyUsedPage);
                }
            }
            pageLastUsed.put(page, pageReferenceString.size());
        }
        return pageFaults;
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        int userInput;
        do {
            System.out.print("Enter the number of frames (1-7): ");
            userInput = scanner.nextInt();
            if (userInput < 1 || userInput > 7) {
                System.out.println("Invalid input! Please enter a number between 1 and 7.");
            }
        } while (userInput < 1 || userInput > 7);
        numFrames = userInput;
        scanner.close();

        System.out.println("Number of frames: " + numFrames);
        System.out.println("FIFO page faults: " + fifo());
        System.out.println("LRU page faults: " + lru());
    }

    public static void main(String[] args) {
        List<Integer> pageReferenceString = generatePageReferenceString(100);

        PageReplacementAlgorithm algorithm = new PageReplacementAlgorithm(pageReferenceString, 0);
        algorithm.run();
    }
}
