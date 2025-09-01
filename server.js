import cors from 'cors';
import express from 'express';

const app = express();
export const PORT = process.env.PORT || 2000;

// ---------- Middleware ---------- //
app.use(cors());
app.use(express.json());

// Route to receive JSON from ESP32
app.post("/esp32/data", (req, res) => {
  const { groupName, temp } = req.body;

  if (!groupName || !temp) {
    return res.status(400).json({ status: "error", message: "Missing groupName or temp in request body" });
  }

  console.log("📩 Data received from ESP32:");
  console.log("Group:", groupName);
  console.log("Temperature:", temp);

  res.status(201).json({ status: "success", message: "Data received successfully" });
});

// Simple route to test server
app.get("/", (req, res) => {
  res.send("ESP32 Express Server is running 🚀");
});

app.listen(PORT, () => {
  console.log(`✅ Server listening at http://localhost:${PORT}`);
});