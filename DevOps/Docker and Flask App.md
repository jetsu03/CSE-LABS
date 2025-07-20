## **Step 1: Install WSL (Windows Subsystem for Linux)**

1. Open **PowerShell** as **Administrator**.
2. Run the following command to install WSL:

   ```powershell
   wsl --install
   ```
3. Restart your system if prompted.

---

## **Step 2: Install Docker Desktop**

1. Go to the Docker official download page:
   🔗 [https://docs.docker.com/desktop/setup/install/windows-install/](https://docs.docker.com/desktop/setup/install/windows-install/)
2. Download and install **Docker Desktop**.
3. After installation:

   * **Restart** your system.
   * Create/log into your **Docker Hub account** if prompted.

---

## **Step 3: Run Docker Commands via CMD**

Open **Command Prompt (cmd)** or **PowerShell**, then execute:

```bash
docker --version           # Check Docker version
docker info                # View system-level Docker details

docker pull ubuntu         # Pull Ubuntu image from Docker Hub
docker run -it ubuntu      # Run Ubuntu container interactively
```

To manage containers:

```bash
docker ps                  # List running containers
docker ps -a               # List all containers (including stopped)
docker stop <container_id> # Stop a running container
docker rm <container_id>   # Remove a container
```

To manage images:

```bash
docker images              # List downloaded Docker images
docker rmi <image_name>    # Remove an image
```

---

## **Step 4: Build and Run a Flask App with Docker**

### A. Create a Project Folder in VS Code

Inside your chosen folder, create the following files:

---

### 1. `app.py`

```python
from flask import Flask
app = Flask(__name__)

@app.route("/")
def home():
    return "Hello from Docker!"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
```

---

### 2. `requirements.txt`

```
flask
```

---

### 3. `Dockerfile`

```Dockerfile
FROM python:3.8-slim
WORKDIR /app
COPY . .
RUN pip install -r requirements.txt

# Run the app
CMD ["python", "app.py"]
```

---

### B. Build and Push Docker Image

Open terminal in the folder (in VS Code or Git Bash), then run:

```bash
docker build -t flask-app .
docker run -d -p 5000:5000 flask-app     # App will be available at http://localhost:5000

docker login                             # Login to Docker Hub
docker tag flask-app your_dockerhub_username/flask-app
docker push your_dockerhub_username/flask-app
```

> Replace `your_dockerhub_username` with your actual Docker Hub username.
