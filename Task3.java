import java.util.ArrayList;
import java.util.List;

public class Task3 {

    private List<Server> servers;
    private int currentServerIndex;

    public Task3(List<Server> servers) {
        this.servers = servers;
        this.currentServerIndex = 0;
    }

    public Server getNextServer() {
        if (servers.isEmpty()) {
            throw new RuntimeException("No servers available");
        }

        Server server = servers.get(currentServerIndex);
        currentServerIndex = (currentServerIndex + 1) % servers.size(); 
        return server;
    }

    public static void main(String[] args) {
        List<Server> servers = new ArrayList<>();
        servers.add(new Server("Server1"));
        servers.add(new Server("Server2"));
        servers.add(new Server("Server3"));

        Task3 loadBalancer = new Task3(servers);

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