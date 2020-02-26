# CHANGELOG

## 0.5

Breaking changes (see the API usage diff below)

1. The way you declare the state machine (`field: value` instead of `.field = value`)

2. No more pointers - they were not necessary.

```diff
diff --git a/example.cpp b/example.cpp
index 77fec20..ee30552 100644
--- a/example.cpp
+++ b/example.cpp
@@ -18,32 +18,32 @@ g++ -std=c++11 ./example.cpp ./src/*.cpp -o example.out
 
 int main() {
 	xs::StateMachine machine = {
-		.id = "light",
-		.initial = "green",
-		.states = {
+		id: "light",
+		state: { value: "green" },
+		states: {
 			{
 				"green" ,
-				{ .on = { { "TIMER", "yellow" } } }
+				{ on = { { "TIMER", "yellow" } } }
 			},
 			{
 				"yellow",
-				{ .on = { { "TIMER", "red"    } } }
+				{ on = { { "TIMER", "red"    } } }
 			},
 			{
 				"red"  ,
 				{
-					.on = { { "TIMER", "red.red-100"  } },
-					.nested = {
-						.id = "red-brightness",
-						.initial = "red-100",
-						.states = {
+					on = { { "TIMER", "red.red-100"  } },
+					nested = {
+						id = "red-brightness",
+						initial = "red-100",
+						states = {
 							{
 								"red-100",
-								{ .on = { { "TIMER", "red.red-0" } } }
+								{ on = { { "TIMER", "red.red-0" } } }
 							},
 							{
 								"red-0",
-								{ .on = { { "TIMER", "green" } } }
+								{ on = { { "TIMER", "green" } } }
 							}
 						}
 					}
@@ -52,34 +52,33 @@ int main() {
 		}
 	};
 
-	xs::Interpreter *toggleMachine = xs::interpret(machine)
-		->logInfo()
-		->onStart([]() {
+	xs::Interpreter toggleMachine = xs::interpret(machine)
+		.logInfo()
+		.onStart([]() {
 			std::cout << "let's go!\n";
 		})
-		->onTransition([](xs::Interpreter *self) {
-			self->logInfo();
+		.onTransition([](xs::Interpreter self) {
+			self.logInfo();
 		})
-		->onStop([]() {
+		.onStop([]() {
 			std::cout << "oh no we stopped c:\n";
 		})
-		->start();
+		.start();
 
-	toggleMachine->send("TIMER");
+	toggleMachine.send("TIMER");
 
-	toggleMachine->send("TIMER");
+	toggleMachine.send("TIMER");
 
-	toggleMachine->send("TIMER");
+	toggleMachine.send("TIMER");
 
-	toggleMachine->send("TIMER");
+	toggleMachine.send("TIMER");
 
-	toggleMachine->send("TIMER");
+	toggleMachine.send("TIMER");
 
-	toggleMachine->send("TIMER");
+	toggleMachine.send("TIMER");
 
-	toggleMachine->stop();
+	toggleMachine.stop();
 
-	delete toggleMachine;
 
 	return 0;
 }

```
