#include "ECTSPlugin.hpp"
#include "ectsTUI.hpp"
#include "SystemMonitoringPlugin.hpp"
int main() {
  ectsTUI tui;
  ECTSPlugin* e1 = new SystemMontitoringPlugin("sddjjj");
  // ECTSPlugin* e2 = new ControlPlugin("jjsdsj");
  ECTSPlugin* e3 = new SystemMontitoringPlugin("jdjd");
  ECTSPlugin* e4 = new SystemMontitoringPlugin("sddjjj");
  ECTSPlugin* e5 = new SystemMontitoringPlugin("jjsdsj");
  ECTSPlugin* e6 = new SystemMontitoringPlugin("jdjd");
  tui.addPlugin(e1);
  // tui.addPlugin(e2);
  tui.addPlugin(e3);
  tui.addPlugin(e4);
  tui.addPlugin(e5);
  tui.addPlugin(e6);
  tui.main();
}