$NetBSD: patch-main_features.c,v 1.2 2012/04/07 20:05:57 jnemeth Exp $

--- main/features.c.orig	2012-02-27 16:05:24.000000000 +0000
+++ main/features.c
@@ -1493,14 +1493,14 @@ static int park_call_full(struct ast_cha
 		"Channel: %s\r\n"
 		"Parkinglot: %s\r\n"
 		"From: %s\r\n"
-		"Timeout: %ld\r\n"
+		"Timeout: %jd\r\n"
 		"CallerIDNum: %s\r\n"
 		"CallerIDName: %s\r\n"
 		"ConnectedLineNum: %s\r\n"
 		"ConnectedLineName: %s\r\n"
 		"Uniqueid: %s\r\n",
 		pu->parkingexten, chan->name, pu->parkinglot->name, event_from,
-		(long)pu->start.tv_sec + (long)(pu->parkingtime/1000) - (long)time(NULL),
+		(intmax_t)pu->start.tv_sec + (intmax_t)(pu->parkingtime/1000) - (intmax_t)time(NULL),
 		S_COR(chan->caller.id.number.valid, chan->caller.id.number.str, "<unknown>"),
 		S_COR(chan->caller.id.name.valid, chan->caller.id.name.str, "<unknown>"),
 		S_COR(chan->connected.id.number.valid, chan->connected.id.number.str, "<unknown>"),
@@ -2057,7 +2057,7 @@ static int builtin_automonitor(struct as
 			len = strlen(touch_monitor) + 50;
 			args = alloca(len);
 			touch_filename = alloca(len);
-			snprintf(touch_filename, len, "%s-%ld-%s", S_OR(touch_monitor_prefix, "auto"), (long)time(NULL), touch_monitor);
+			snprintf(touch_filename, len, "%s-%jd-%s", S_OR(touch_monitor_prefix, "auto"), (intmax_t)time(NULL), touch_monitor);
 			snprintf(args, len, "%s,%s,m", S_OR(touch_format, "wav"), touch_filename);
 		} else {
 			caller_chan_id = ast_strdupa(S_COR(caller_chan->caller.id.number.valid,
@@ -2067,7 +2067,7 @@ static int builtin_automonitor(struct as
 			len = strlen(caller_chan_id) + strlen(callee_chan_id) + 50;
 			args = alloca(len);
 			touch_filename = alloca(len);
-			snprintf(touch_filename, len, "%s-%ld-%s-%s", S_OR(touch_monitor_prefix, "auto"), (long)time(NULL), caller_chan_id, callee_chan_id);
+			snprintf(touch_filename, len, "%s-%jd-%s-%s", S_OR(touch_monitor_prefix, "auto"), (intmax_t)time(NULL), caller_chan_id, callee_chan_id);
 			snprintf(args, len, "%s,%s,m", S_OR(touch_format, "wav"), touch_filename);
 		}
 
@@ -2173,7 +2173,7 @@ static int builtin_automixmonitor(struct
 			len = strlen(touch_monitor) + 50;
 			args = alloca(len);
 			touch_filename = alloca(len);
-			snprintf(touch_filename, len, "auto-%ld-%s", (long)time(NULL), touch_monitor);
+			snprintf(touch_filename, len, "auto-%jd-%s", (intmax_t)time(NULL), touch_monitor);
 			snprintf(args, len, "%s.%s,b", touch_filename, (touch_format) ? touch_format : "wav");
 		} else {
 			caller_chan_id = ast_strdupa(S_COR(caller_chan->caller.id.number.valid,
@@ -2183,7 +2183,7 @@ static int builtin_automixmonitor(struct
 			len = strlen(caller_chan_id) + strlen(callee_chan_id) + 50;
 			args = alloca(len);
 			touch_filename = alloca(len);
-			snprintf(touch_filename, len, "auto-%ld-%s-%s", (long)time(NULL), caller_chan_id, callee_chan_id);
+			snprintf(touch_filename, len, "auto-%jd-%s-%s", (intmax_t)time(NULL), caller_chan_id, callee_chan_id);
 			snprintf(args, len, "%s.%s,b", touch_filename, S_OR(touch_format, "wav"));
 		}
 
@@ -6973,10 +6973,10 @@ static char *handle_parkedcalls(struct a
 
 		AST_LIST_LOCK(&curlot->parkings);
 		AST_LIST_TRAVERSE(&curlot->parkings, cur, list) {
-			ast_cli(a->fd, "%-10.10s %-25s (%-15s %-12s %4d) %6lds\n",
+			ast_cli(a->fd, "%-10.10s %-25s (%-15s %-12s %4d) %6jds\n",
 				cur->parkingexten, cur->chan->name, cur->context, cur->exten,
 				cur->priority,
-				(long) (cur->start.tv_sec + (cur->parkingtime / 1000) - time(NULL)));
+				(intmax_t) (cur->start.tv_sec + (cur->parkingtime / 1000) - time(NULL)));
 			++lotparked;
 		}
 		AST_LIST_UNLOCK(&curlot->parkings);
@@ -7032,7 +7032,7 @@ static int manager_parking_status(struct
 				"Exten: %d\r\n"
 				"Channel: %s\r\n"
 				"From: %s\r\n"
-				"Timeout: %ld\r\n"
+				"Timeout: %jd\r\n"
 				"CallerIDNum: %s\r\n"
 				"CallerIDName: %s\r\n"
 				"ConnectedLineNum: %s\r\n"
@@ -7041,7 +7041,7 @@ static int manager_parking_status(struct
 				"\r\n",
 				curlot->name,
 				cur->parkingnum, cur->chan->name, cur->peername,
-				(long) cur->start.tv_sec + (long) (cur->parkingtime / 1000) - (long) time(NULL),
+				(intmax_t) cur->start.tv_sec + (intmax_t) (cur->parkingtime / 1000) - (intmax_t) time(NULL),
 				S_COR(cur->chan->caller.id.number.valid, cur->chan->caller.id.number.str, ""),	/* XXX in other places it is <unknown> */
 				S_COR(cur->chan->caller.id.name.valid, cur->chan->caller.id.name.str, ""),
 				S_COR(cur->chan->connected.id.number.valid, cur->chan->connected.id.number.str, ""),	/* XXX in other places it is <unknown> */
