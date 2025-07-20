## **Step 1: Install JDK 21**

1. Download JDK 21 from:
   🔗 [https://www.oracle.com/java/technologies/javase/jdk21-archive-downloads.html](https://www.oracle.com/java/technologies/javase/jdk21-archive-downloads.html)

2. Install the JDK.

3. Set **Environment Variables**:

   * `JAVA_HOME = C:\Program Files\Java\jdk-21`
   * Add `%JAVA_HOME%\bin` to the system **Path** variable.

4. Open CMD and verify installation:

   ```bash
   java -version
   javac -version
   ```

---

## **Step 2: Install Maven**

1. Download Apache Maven (binary ZIP):
   🔗 [https://maven.apache.org/download.cgi](https://maven.apache.org/download.cgi)
   → Choose version **3.9.10** ZIP file.

2. Extract to a folder (e.g., `C:\Maven\apache-maven-3.9.10`).

3. Set **System Environment Variables**:

   * `MAVEN_HOME = C:\Maven\apache-maven-3.9.10`
   * Add `%MAVEN_HOME%\bin` to the system **Path**.

4. Open CMD and verify Maven:

   ```bash
   mvn -v
   ```

---

## **Step 3: Generate a Maven Project**

1. Open CMD and run the following:

   ```bash
   mvn archetype:generate -DgroupId=com.example -DartifactId=demo-project -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false
   ```

2. This creates a new folder named `demo-project/` with a Maven project structure.

---

## **Step 4: Update `pom.xml` with Dependencies**

Open `demo-project/pom.xml` and replace the contents with:

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/maven-v4_0_0.xsd">

  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>demo-project</artifactId>
  <packaging>jar</packaging>
  <version>1.0-SNAPSHOT</version>
  <name>demo-project</name>
  <url>http://maven.apache.org</url>

  <dependencies>
    <!-- Gson for JSON handling -->
    <dependency>
      <groupId>com.google.code.gson</groupId>
      <artifactId>gson</artifactId>
      <version>2.10.1</version>
      <scope>test</scope>
    </dependency>

    <!-- JUnit for testing -->
    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.13.2</version>
      <scope>test</scope>
    </dependency>
  </dependencies>
</project>
```

---

## **Step 5: Build, Test, and Run the Project**

### A. Open CMD and go to the project directory:

```bash
cd demo-project
```

### B. Compile the project:

```bash
mvn compile
```

### C. Run tests:

```bash
mvn test
```

### D. Package the project:

```bash
mvn package
```

This creates a JAR file:
`target/demo-project-1.0-SNAPSHOT.jar`

---

## **Step 6: Run the Java App**

To execute the `App.java` file:

```bash
java -cp target/demo-project-1.0-SNAPSHOT.jar com.example.App
```

You should see:

```
Hello World!
```

> If you later include Gson functionality in your `App.java`, make sure to add Gson as a runtime dependency (remove `<scope>test</scope>` from the Gson dependency).
