/**
 *  Multi-switch Controller (device handler)
 *
 *  Author: davidebliss@gmail.com
 *  Date: 2013-03-14
 *  Capabilities:
 *   Switch Level
 *  Custom Attributes:
 *   switch1
 *   switch2
 *   switch3
 *   switch4
 *   switch5
 *   knob1
 *  Custom Commands
 *   on1/off1
 *   on2/off2
 *   on3/off3
 *   on4/off4
 *   on5/off5
 */
 
// for the UI
metadata {
	// tile definitions
	tiles {
        standardTile("switch1", "switch1", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state "on1", label: 'on 1', action: "off1", backgroundColor: "#79b821"
			state "off1", label: 'off 1', action: "on1", backgroundColor: "#ffffff"
		}
		standardTile("switch2", "switch2", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state "on2", label: 'on 2', action: "off2", backgroundColor: "#79b821"
			state "off2", label: 'off 2', action: "on2", backgroundColor: "#ffffff"
		}
        standardTile("switch3", "switch3", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state "on3", label: 'on 3', action: "off3", backgroundColor: "#79b821"
			state "off3", label: 'off 3', action: "on3", backgroundColor: "#ffffff"
		}
        standardTile("switch4", "switch4", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state "on4", label: 'on 4', action: "off4", backgroundColor: "#79b821"
			state "off4", label: 'off 4', action: "on4", backgroundColor: "#ffffff"
		}
        standardTile("switch5", "switch5", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
			state "on5", label: 'on 5', action: "off5", backgroundColor: "#79b821"
			state "off5", label: 'off 5', action: "on5", backgroundColor: "#ffffff"
		}
        controlTile("knob1", "device.level", "slider", height: 1, width: 3, inactiveLabel: false) {
			state "level", action:"switch level.setLevel"
		}
        valueTile("level", "device.level", inactiveLabel: false, decoration: "flat") {
            state "level", label: 'Level ${currentValue}%'
        }
        
		main "switch3"
		details(["switch1", "switch2", "switch3", "switch4", "switch5", "knob1", "level"])
	}
	
    simulator {
       
    }
}
 
def on1() {
	log.debug "on1 called in device handler"
    zigbee.smartShield(text: "on").format()
}
 
def off1() {
	log.debug "off1 called in device handler"
	zigbee.smartShield(text: "off").format()
}

def on2() {
	log.debug "on2 called in device handler"
    zigbee.smartShield(text: "on2").format()
}
 
def off2() {
	log.debug "off2 called in device handler"
	zigbee.smartShield(text: "off2").format()
}

def on3() {
	log.debug "on3 called in device handler"
    zigbee.smartShield(text: "on3").format()
}
 
def off3() {
	log.debug "off3 called in device handler"
	zigbee.smartShield(text: "off3").format()
}

def on4() {
	log.debug "on4 called in device handler"
	zigbee.smartShield(text: "on4").format()
}

def off4() {
	log.debug "off4 called in device handler"
	zigbee.smartShield(text: "off4").format()
}

def on5() {
	log.debug "on5 called in device handler"
	zigbee.smartShield(text: "on5").format()
}

def off5() {
	log.debug "off5 called in device handler"
	zigbee.smartShield(text: "off5").format()
} 

def setLevel(level) {
	log.debug "setLevel called in device handler"
	zigbee.smartShield(text: "setLevel1:$level").format()
} 

def parse(String description) {
	log.debug "Parsing '${description}'"
    
	def value = zigbee.parse(description)?.text
    log.debug "value: '${value}'"
    def name = "noone"
    
    if (value in ["on1","off1"]) {
    	name = "switch1"
    } else if (value in ["on2","off2"]) {
    	name = "switch2"
    } else if (value in ["on3","off3"]) {
    	name = "switch3"
    } else if (value in ["on4","off4"]) {
    	name = "switch4"
    } else if (value in ["on5","off5"]) {
    	name = "switch5"
    } else if (value.startsWith('setLevel1:')){
    	value -= "setLevel1:"
        value = value.trim()
    	log.debug "setLevel detected"
        log.debug value
        name = "level"
    } 
    
	def result = createEvent(name: name, value: value)
	// e.g. 
    // def result = createEvent(name: "contact", value: "closed")
    
    log.debug "Parse returned ${result?.descriptionText}"
	
    return result
}