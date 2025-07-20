## **EXP-3: Microservice App using Docker Compose**

---

## **Step 1: Project Folder Structure**

Create the following folder structure:

```
microservice-app/
│
├── docker-compose.yml           # Orchestrates both services
│
├── app/                         # Flask microservice
│   ├── app.py                   # Flask app code
│   ├── requirements.txt         # Python dependencies
│   └── Dockerfile               # Docker instructions for Flask app
```

---

## **Step 2: File Contents**

### `app/app.py`

```python
from flask import Flask
app = Flask(__name__)

@app.route('/')
def home():
    return "Hello from Microservice App!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
```

---

### `app/requirements.txt`

```
flask
```

---

### `app/Dockerfile`

```Dockerfile
FROM python:3.9
WORKDIR /app
COPY requirements.txt .
RUN pip install -r requirements.txt
COPY . .
CMD ["python", "app.py"]
```

---

### `docker-compose.yml`

```yaml
version: '3'
services:
  web:
    build: ./app
    ports:
      - "5000:5000"       # Access Flask app at http://localhost:5000
    depends_on:
      - db

  db:
    image: mysql:5.7
    restart: always
    environment:
      MYSQL_DATABASE: sampledb
      MYSQL_USER: user
      MYSQL_PASSWORD: password
      MYSQL_ROOT_PASSWORD: rootpass
    ports:
      - "3306:3306"
```

---

## **Step 3: Run the App**

### To build and run the services:

```bash
docker-compose up --build
```

* Open your browser and visit:
  🔗 **[http://localhost:5000](http://localhost:5000)**

### To stop and remove containers:

```bash
docker-compose down
```

---

## **Step 4: Push Image to Docker Hub (Optional)**

1. Make sure you're logged in:

   ```bash
   docker login
   ```

2. Tag your image:

   ```bash
   docker tag flask-app your_dockerhub_username/flask-app
   ```

3. Push it:

   ```bash
   docker push your_dockerhub_username/flask-app
   ```

> Replace `your_dockerhub_username` with your actual Docker Hub username.
