import java.util.ArrayList;
import java.util.List;

public class Task2 {

    private List<Server> servers;
    private int server1Count; // Tracks requests handled by Server1
    private final int server1Quota; // Maximum requests for Server1

    public Task2(List<Server> servers, int server1Quota) {
        this.servers = servers;
        this.server1Count = 0;
        this.server1Quota = server1Quota;
    }

    public Server getNextServer() {
        if (servers.isEmpty()) {
            throw new RuntimeException("No servers available");
        }

        if (server1Count < server1Quota) {
            server1Count++;
            return servers.get(0); // Server1
        } else {
            return servers.get(1); // Server2
        }
    }

    public static void main(String[] args) {
        List<Server> servers = new ArrayList<>();
        servers.add(new Server("Server1"));
        servers.add(new Server("Server2"));
        servers.add(new Server("Server3"));

        // Assign 10 requests to Server1 and 5 to Server2
        int server1Quota = 10;
        Task2 loadBalancer = new Task2(servers, server1Quota);

        for (int i = 0; i < 15; i++) {
            Server server = loadBalancer.getNextServer();
            System.out.println("Request " + (i + 1) + " handled by: " + server.getName());
        }
    }
}

class Server {
    private String name;

    public Server(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}