#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include <opentelemetry/sdk/trace/exporter.h>
#include <opentelemetry/sdk/trace/processor.h>
#include <opentelemetry/trace/provider.h>

#include <opentelemetry/exporters/ostream/span_exporter_factory.h>
#include <opentelemetry/sdk/trace/simple_processor_factory.h>
#include <opentelemetry/sdk/trace/tracer_provider_factory.h>

void run() {
  auto tracer = opentelemetry::trace::Provider::GetTracerProvider()->GetTracer(
      "my-app-tracer");
  auto span = tracer->StartSpan("RollDiceServer");
  int low = 1;
  int high = 7;
  int random = std::rand() % (high - low) + low;
  const std::string result = "Rolled a " + std::to_string(random);
  span->End();
  std::cout << result << std::endl;
}

int main(int argc, char **argv) {
  auto exporter =
      opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();

  auto processor =
      opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(
          std::move(exporter));

  std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
      opentelemetry::sdk::trace::TracerProviderFactory::Create(
          std::move(processor));

  opentelemetry::trace::Provider::SetTracerProvider(provider);

  run();

  std::shared_ptr<opentelemetry::trace::TracerProvider> none;
  opentelemetry::trace::Provider::SetTracerProvider(none);

  return 0;
}
